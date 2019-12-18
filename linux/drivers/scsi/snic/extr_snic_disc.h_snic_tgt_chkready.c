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
struct snic_tgt {scalar_t__ state; } ;

/* Variables and functions */
 int DID_NO_CONNECT ; 
 scalar_t__ SNIC_TGT_STAT_ONLINE ; 

__attribute__((used)) static inline int
snic_tgt_chkready(struct snic_tgt *tgt)
{
	if (tgt->state == SNIC_TGT_STAT_ONLINE)
		return 0;
	else
		return DID_NO_CONNECT << 16;
}