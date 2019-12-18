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
typedef  int /*<<< orphan*/  u32 ;
struct radio_isa_card {int /*<<< orphan*/  io; } ;

/* Variables and functions */
 int GEMTEK_NS ; 
 int /*<<< orphan*/  V4L2_TUNER_SUB_MONO ; 
 int /*<<< orphan*/  V4L2_TUNER_SUB_STEREO ; 
 int inb_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 gemtek_g_rxsubchans(struct radio_isa_card *isa)
{
	if (inb_p(isa->io) & GEMTEK_NS)
		return V4L2_TUNER_SUB_MONO;
	return V4L2_TUNER_SUB_STEREO;
}