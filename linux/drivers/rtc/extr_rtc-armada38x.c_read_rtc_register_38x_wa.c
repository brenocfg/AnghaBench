#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct armada38x_rtc {TYPE_1__* val_to_freq; scalar_t__ regs; } ;
struct TYPE_2__ {scalar_t__ value; int freq; } ;

/* Variables and functions */
 int SAMPLE_NR ; 
 scalar_t__ readl (scalar_t__) ; 

__attribute__((used)) static u32 read_rtc_register_38x_wa(struct armada38x_rtc *rtc, u8 rtc_reg)
{
	int i, index_max = 0, max = 0;

	for (i = 0; i < SAMPLE_NR; i++) {
		rtc->val_to_freq[i].value = readl(rtc->regs + rtc_reg);
		rtc->val_to_freq[i].freq = 0;
	}

	for (i = 0; i < SAMPLE_NR; i++) {
		int j = 0;
		u32 value = rtc->val_to_freq[i].value;

		while (rtc->val_to_freq[j].freq) {
			if (rtc->val_to_freq[j].value == value) {
				rtc->val_to_freq[j].freq++;
				break;
			}
			j++;
		}

		if (!rtc->val_to_freq[j].freq) {
			rtc->val_to_freq[j].value = value;
			rtc->val_to_freq[j].freq = 1;
		}

		if (rtc->val_to_freq[j].freq > max) {
			index_max = j;
			max = rtc->val_to_freq[j].freq;
		}

		/*
		 * If a value already has half of the sample this is the most
		 * frequent one and we can stop the research right now
		 */
		if (max > SAMPLE_NR / 2)
			break;
	}

	return rtc->val_to_freq[index_max].value;
}