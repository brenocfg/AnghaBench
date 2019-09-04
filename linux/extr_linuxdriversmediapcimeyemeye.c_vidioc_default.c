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
struct meye_params {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 long ENOTTY ; 
#define  MEYEIOC_G_PARAMS 133 
#define  MEYEIOC_QBUF_CAPT 132 
#define  MEYEIOC_STILLCAPT 131 
#define  MEYEIOC_STILLJCAPT 130 
#define  MEYEIOC_SYNC 129 
#define  MEYEIOC_S_PARAMS 128 
 long meyeioc_g_params (struct meye_params*) ; 
 long meyeioc_qbuf_capt (int*) ; 
 long meyeioc_s_params (struct meye_params*) ; 
 long meyeioc_stillcapt () ; 
 long meyeioc_stilljcapt (int*) ; 
 long meyeioc_sync (struct file*,void*,int*) ; 

__attribute__((used)) static long vidioc_default(struct file *file, void *fh, bool valid_prio,
			   unsigned int cmd, void *arg)
{
	switch (cmd) {
	case MEYEIOC_G_PARAMS:
		return meyeioc_g_params((struct meye_params *) arg);

	case MEYEIOC_S_PARAMS:
		return meyeioc_s_params((struct meye_params *) arg);

	case MEYEIOC_QBUF_CAPT:
		return meyeioc_qbuf_capt((int *) arg);

	case MEYEIOC_SYNC:
		return meyeioc_sync(file, fh, (int *) arg);

	case MEYEIOC_STILLCAPT:
		return meyeioc_stillcapt();

	case MEYEIOC_STILLJCAPT:
		return meyeioc_stilljcapt((int *) arg);

	default:
		return -ENOTTY;
	}

}