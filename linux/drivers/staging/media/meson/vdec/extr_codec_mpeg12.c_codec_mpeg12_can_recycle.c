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
struct amvdec_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MREG_BUFFERIN ; 
 int /*<<< orphan*/  amvdec_read_dos (struct amvdec_core*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int codec_mpeg12_can_recycle(struct amvdec_core *core)
{
	return !amvdec_read_dos(core, MREG_BUFFERIN);
}