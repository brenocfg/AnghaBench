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
struct hid_input {TYPE_1__* input; } ;
struct TYPE_2__ {unsigned long* evbit; unsigned long* keybit; unsigned long* relbit; unsigned long* absbit; unsigned long* mscbit; unsigned long* ledbit; unsigned long* sndbit; unsigned long* ffbit; unsigned long* swbit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_CNT ; 
 int BITS_TO_LONGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EV_CNT ; 
 int /*<<< orphan*/  FF_CNT ; 
 int /*<<< orphan*/  KEY_CNT ; 
 int /*<<< orphan*/  LED_CNT ; 
 int /*<<< orphan*/  MSC_CNT ; 
 int /*<<< orphan*/  REL_CNT ; 
 int /*<<< orphan*/  SND_CNT ; 
 int /*<<< orphan*/  SW_CNT ; 

__attribute__((used)) static bool hidinput_has_been_populated(struct hid_input *hidinput)
{
	int i;
	unsigned long r = 0;

	for (i = 0; i < BITS_TO_LONGS(EV_CNT); i++)
		r |= hidinput->input->evbit[i];

	for (i = 0; i < BITS_TO_LONGS(KEY_CNT); i++)
		r |= hidinput->input->keybit[i];

	for (i = 0; i < BITS_TO_LONGS(REL_CNT); i++)
		r |= hidinput->input->relbit[i];

	for (i = 0; i < BITS_TO_LONGS(ABS_CNT); i++)
		r |= hidinput->input->absbit[i];

	for (i = 0; i < BITS_TO_LONGS(MSC_CNT); i++)
		r |= hidinput->input->mscbit[i];

	for (i = 0; i < BITS_TO_LONGS(LED_CNT); i++)
		r |= hidinput->input->ledbit[i];

	for (i = 0; i < BITS_TO_LONGS(SND_CNT); i++)
		r |= hidinput->input->sndbit[i];

	for (i = 0; i < BITS_TO_LONGS(FF_CNT); i++)
		r |= hidinput->input->ffbit[i];

	for (i = 0; i < BITS_TO_LONGS(SW_CNT); i++)
		r |= hidinput->input->swbit[i];

	return !!r;
}