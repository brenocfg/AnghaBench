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
struct saa7134_dev {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSP_DELAY ; 
 int DSP_RETRY ; 
 int EIO ; 
 int /*<<< orphan*/  SAA7135_DSP_RWSTATE ; 
 int SAA7135_DSP_RWSTATE_ERR ; 
 int SAA7135_DSP_RWSTATE_IDA ; 
 int SAA7135_DSP_RWSTATE_RDB ; 
 int SAA7135_DSP_RWSTATE_WRR ; 
 int /*<<< orphan*/  pr_err (char*,char*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa_dsp_reset_error_bit (struct saa7134_dev*) ; 
 int saa_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa_wait (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int saa_dsp_wait_bit(struct saa7134_dev *dev, int bit)
{
	int state, count = DSP_RETRY;

	state = saa_readb(SAA7135_DSP_RWSTATE);
	if (unlikely(state & SAA7135_DSP_RWSTATE_ERR)) {
		pr_warn("%s: dsp access error\n", dev->name);
		saa_dsp_reset_error_bit(dev);
		return -EIO;
	}
	while (0 == (state & bit)) {
		if (unlikely(0 == count)) {
			pr_err("dsp access wait timeout [bit=%s]\n",
				 (bit & SAA7135_DSP_RWSTATE_WRR) ? "WRR" :
				 (bit & SAA7135_DSP_RWSTATE_RDB) ? "RDB" :
				 (bit & SAA7135_DSP_RWSTATE_IDA) ? "IDA" :
				 "???");
			return -EIO;
		}
		saa_wait(DSP_DELAY);
		state = saa_readb(SAA7135_DSP_RWSTATE);
		count--;
	}
	return 0;
}