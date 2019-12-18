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

/* Variables and functions */
 int BNXT_QPLIB_ACCESS_LOCAL_WRITE ; 
 int BNXT_QPLIB_ACCESS_MW_BIND ; 
 int BNXT_QPLIB_ACCESS_ON_DEMAND ; 
 int BNXT_QPLIB_ACCESS_REMOTE_ATOMIC ; 
 int BNXT_QPLIB_ACCESS_REMOTE_READ ; 
 int BNXT_QPLIB_ACCESS_REMOTE_WRITE ; 
 int BNXT_QPLIB_ACCESS_ZERO_BASED ; 
 int IB_ACCESS_LOCAL_WRITE ; 
 int IB_ACCESS_MW_BIND ; 
 int IB_ACCESS_ON_DEMAND ; 
 int IB_ACCESS_REMOTE_ATOMIC ; 
 int IB_ACCESS_REMOTE_READ ; 
 int IB_ACCESS_REMOTE_WRITE ; 
 int IB_ZERO_BASED ; 

__attribute__((used)) static int __from_ib_access_flags(int iflags)
{
	int qflags = 0;

	if (iflags & IB_ACCESS_LOCAL_WRITE)
		qflags |= BNXT_QPLIB_ACCESS_LOCAL_WRITE;
	if (iflags & IB_ACCESS_REMOTE_READ)
		qflags |= BNXT_QPLIB_ACCESS_REMOTE_READ;
	if (iflags & IB_ACCESS_REMOTE_WRITE)
		qflags |= BNXT_QPLIB_ACCESS_REMOTE_WRITE;
	if (iflags & IB_ACCESS_REMOTE_ATOMIC)
		qflags |= BNXT_QPLIB_ACCESS_REMOTE_ATOMIC;
	if (iflags & IB_ACCESS_MW_BIND)
		qflags |= BNXT_QPLIB_ACCESS_MW_BIND;
	if (iflags & IB_ZERO_BASED)
		qflags |= BNXT_QPLIB_ACCESS_ZERO_BASED;
	if (iflags & IB_ACCESS_ON_DEMAND)
		qflags |= BNXT_QPLIB_ACCESS_ON_DEMAND;
	return qflags;
}