#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct igb_reg_test {scalar_t__ reg; scalar_t__ array_len; int test_type; scalar_t__ reg_offset; int /*<<< orphan*/  write; int /*<<< orphan*/  mask; } ;
struct TYPE_3__ {int type; } ;
struct e1000_hw {scalar_t__ hw_addr; TYPE_1__ mac; } ;
struct igb_adapter {struct e1000_hw hw; TYPE_2__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_STATUS ; 
#define  PATTERN_TEST 139 
 int /*<<< orphan*/  REG_PATTERN_TEST (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_AND_CHECK (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  SET_READ_TEST 138 
#define  TABLE32_TEST 137 
#define  TABLE64_TEST_HI 136 
#define  TABLE64_TEST_LO 135 
#define  WRITE_NO_TEST 134 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__) ; 
#define  e1000_82576 133 
#define  e1000_82580 132 
#define  e1000_i210 131 
#define  e1000_i211 130 
#define  e1000_i350 129 
#define  e1000_i354 128 
 scalar_t__ rd32 (int /*<<< orphan*/ ) ; 
 struct igb_reg_test* reg_test_82575 ; 
 struct igb_reg_test* reg_test_82576 ; 
 struct igb_reg_test* reg_test_82580 ; 
 struct igb_reg_test* reg_test_i210 ; 
 struct igb_reg_test* reg_test_i350 ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int igb_reg_test(struct igb_adapter *adapter, u64 *data)
{
	struct e1000_hw *hw = &adapter->hw;
	struct igb_reg_test *test;
	u32 value, before, after;
	u32 i, toggle;

	switch (adapter->hw.mac.type) {
	case e1000_i350:
	case e1000_i354:
		test = reg_test_i350;
		toggle = 0x7FEFF3FF;
		break;
	case e1000_i210:
	case e1000_i211:
		test = reg_test_i210;
		toggle = 0x7FEFF3FF;
		break;
	case e1000_82580:
		test = reg_test_82580;
		toggle = 0x7FEFF3FF;
		break;
	case e1000_82576:
		test = reg_test_82576;
		toggle = 0x7FFFF3FF;
		break;
	default:
		test = reg_test_82575;
		toggle = 0x7FFFF3FF;
		break;
	}

	/* Because the status register is such a special case,
	 * we handle it separately from the rest of the register
	 * tests.  Some bits are read-only, some toggle, and some
	 * are writable on newer MACs.
	 */
	before = rd32(E1000_STATUS);
	value = (rd32(E1000_STATUS) & toggle);
	wr32(E1000_STATUS, toggle);
	after = rd32(E1000_STATUS) & toggle;
	if (value != after) {
		dev_err(&adapter->pdev->dev,
			"failed STATUS register test got: 0x%08X expected: 0x%08X\n",
			after, value);
		*data = 1;
		return 1;
	}
	/* restore previous status */
	wr32(E1000_STATUS, before);

	/* Perform the remainder of the register test, looping through
	 * the test table until we either fail or reach the null entry.
	 */
	while (test->reg) {
		for (i = 0; i < test->array_len; i++) {
			switch (test->test_type) {
			case PATTERN_TEST:
				REG_PATTERN_TEST(test->reg +
						(i * test->reg_offset),
						test->mask,
						test->write);
				break;
			case SET_READ_TEST:
				REG_SET_AND_CHECK(test->reg +
						(i * test->reg_offset),
						test->mask,
						test->write);
				break;
			case WRITE_NO_TEST:
				writel(test->write,
				    (adapter->hw.hw_addr + test->reg)
					+ (i * test->reg_offset));
				break;
			case TABLE32_TEST:
				REG_PATTERN_TEST(test->reg + (i * 4),
						test->mask,
						test->write);
				break;
			case TABLE64_TEST_LO:
				REG_PATTERN_TEST(test->reg + (i * 8),
						test->mask,
						test->write);
				break;
			case TABLE64_TEST_HI:
				REG_PATTERN_TEST((test->reg + 4) + (i * 8),
						test->mask,
						test->write);
				break;
			}
		}
		test++;
	}

	*data = 0;
	return 0;
}