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
typedef  unsigned long long u32 ;
struct ddb {TYPE_2__* link; } ;
typedef  enum fe_sec_tone_mode { ____Placeholder_fe_sec_tone_mode } fe_sec_tone_mode ;
struct TYPE_3__ {unsigned long long tone; } ;
struct TYPE_4__ {TYPE_1__ lnb; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LNB_CMD_NOP ; 
#define  SEC_TONE_OFF 129 
#define  SEC_TONE_ON 128 
 int lnb_command (struct ddb*,unsigned long long,unsigned long long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lnb_set_tone(struct ddb *dev, u32 link, u32 input,
			enum fe_sec_tone_mode tone)
{
	int s = 0;
	u32 mask = (1ULL << input);

	switch (tone) {
	case SEC_TONE_OFF:
		if (!(dev->link[link].lnb.tone & mask))
			return 0;
		dev->link[link].lnb.tone &= ~(1ULL << input);
		break;
	case SEC_TONE_ON:
		if (dev->link[link].lnb.tone & mask)
			return 0;
		dev->link[link].lnb.tone |= (1ULL << input);
		break;
	default:
		s = -EINVAL;
		break;
	}
	if (!s)
		s = lnb_command(dev, link, input, LNB_CMD_NOP);
	return s;
}