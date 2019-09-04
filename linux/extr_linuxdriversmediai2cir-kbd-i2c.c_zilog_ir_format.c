#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct rc_dev {int /*<<< orphan*/  dev; struct IR_i2c* priv; } ;
struct code_block {int* space; int* pulse; int* codes; void* carrier_space; void* carrier_pulse; } ;
struct IR_i2c {int duty_cycle; int carrier; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 void* DIV_ROUND_CLOSEST (int,int) ; 
 int EINVAL ; 
 int XTAL_FREQ ; 
 int /*<<< orphan*/  cmp_no_trail (int*,int*,int) ; 
 int /*<<< orphan*/  copy_codes (int*,int*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int find_slot (int*,int,int) ; 
 scalar_t__ get_unaligned_be16 (int*) ; 
 int /*<<< orphan*/  memcmp (int*,int*,int) ; 

__attribute__((used)) static int zilog_ir_format(struct rc_dev *rcdev, unsigned int *txbuf,
			   unsigned int count, struct code_block *code_block)
{
	struct IR_i2c *ir = rcdev->priv;
	int rep, i, l, p = 0, s, c = 0;
	bool repeating;
	u8 codes[174];

	code_block->carrier_pulse = DIV_ROUND_CLOSEST(
			ir->duty_cycle * XTAL_FREQ / 1000, ir->carrier);
	code_block->carrier_space = DIV_ROUND_CLOSEST(
			(100 - ir->duty_cycle) * XTAL_FREQ / 1000, ir->carrier);

	for (i = 0; i < count; i++) {
		if (c >= ARRAY_SIZE(codes) - 1) {
			dev_warn(&rcdev->dev, "IR too long, cannot transmit\n");
			return -EINVAL;
		}

		/*
		 * Lengths more than 142220us cannot be encoded; also
		 * this checks for multiply overflow
		 */
		if (txbuf[i] > 142220)
			return -EINVAL;

		l = DIV_ROUND_CLOSEST((XTAL_FREQ / 1000) * txbuf[i], 40000);

		if (i & 1) {
			s = find_slot(code_block->space,
				      ARRAY_SIZE(code_block->space), l);
			if (s == -1) {
				dev_warn(&rcdev->dev, "Too many different lengths spaces, cannot transmit");
				return -EINVAL;
			}

			/* We have a pulse and space */
			codes[c++] = (p << 4) | s;
		} else {
			p = find_slot(code_block->pulse,
				      ARRAY_SIZE(code_block->pulse), l);
			if (p == -1) {
				dev_warn(&rcdev->dev, "Too many different lengths pulses, cannot transmit");
				return -EINVAL;
			}
		}
	}

	/* We have to encode the trailing pulse. Find the shortest space */
	s = 0;
	for (i = 1; i < ARRAY_SIZE(code_block->space); i++) {
		u16 d = get_unaligned_be16(&code_block->space[i]);

		if (get_unaligned_be16(&code_block->space[s]) > d)
			s = i;
	}

	codes[c++] = (p << 4) | s;

	dev_dbg(&rcdev->dev, "generated %d codes\n", c);

	/*
	 * Are the last N codes (so pulse + space) repeating 3 times?
	 * if so we can shorten the codes list and use code 0xc0 to repeat
	 * them.
	 */
	repeating = false;

	for (rep = c / 3; rep >= 1; rep--) {
		if (!memcmp(&codes[c - rep * 3], &codes[c - rep * 2], rep) &&
		    !cmp_no_trail(&codes[c - rep], &codes[c - rep * 2], rep)) {
			repeating = true;
			break;
		}
	}

	if (repeating) {
		/* first copy any leading non-repeating */
		int leading = c - rep * 3;

		if (leading >= ARRAY_SIZE(code_block->codes) - 3 - rep) {
			dev_warn(&rcdev->dev, "IR too long, cannot transmit\n");
			return -EINVAL;
		}

		dev_dbg(&rcdev->dev, "found trailing %d repeat\n", rep);
		copy_codes(code_block->codes, codes, leading);
		code_block->codes[leading] = 0x82;
		copy_codes(code_block->codes + leading + 1, codes + leading,
			   rep);
		c = leading + 1 + rep;
		code_block->codes[c++] = 0xc0;
	} else {
		if (c >= ARRAY_SIZE(code_block->codes) - 3) {
			dev_warn(&rcdev->dev, "IR too long, cannot transmit\n");
			return -EINVAL;
		}

		dev_dbg(&rcdev->dev, "found no trailing repeat\n");
		code_block->codes[0] = 0x82;
		copy_codes(code_block->codes + 1, codes, c);
		c++;
		code_block->codes[c++] = 0xc4;
	}

	while (c < ARRAY_SIZE(code_block->codes))
		code_block->codes[c++] = 0x83;

	return 0;
}