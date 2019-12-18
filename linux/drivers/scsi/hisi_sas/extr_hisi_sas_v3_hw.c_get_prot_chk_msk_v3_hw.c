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
typedef  int u32 ;
struct scsi_cmnd {unsigned char prot_flags; } ;

/* Variables and functions */
 unsigned char SCSI_PROT_REF_CHECK ; 
 int T10_CHK_APP_TAG_MSK ; 
 int T10_CHK_REF_TAG_MSK ; 

__attribute__((used)) static u32 get_prot_chk_msk_v3_hw(struct scsi_cmnd *scsi_cmnd)
{
	unsigned char prot_flags = scsi_cmnd->prot_flags;

	if (prot_flags & SCSI_PROT_REF_CHECK)
		return T10_CHK_APP_TAG_MSK;
	return T10_CHK_REF_TAG_MSK | T10_CHK_APP_TAG_MSK;
}