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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_ACCESS_FLAGS_BIND_WINDOW ; 
 int /*<<< orphan*/  I40IW_ACCESS_FLAGS_LOCALWRITE ; 
 int /*<<< orphan*/  I40IW_ACCESS_FLAGS_REMOTEREAD ; 
 int /*<<< orphan*/  I40IW_ACCESS_FLAGS_REMOTEWRITE ; 
 int IB_ACCESS_LOCAL_WRITE ; 
 int IB_ACCESS_MW_BIND ; 
 int IB_ACCESS_REMOTE_READ ; 
 int IB_ACCESS_REMOTE_WRITE ; 

__attribute__((used)) static inline u16 i40iw_get_user_access(int acc)
{
	u16 access = 0;

	access |= (acc & IB_ACCESS_LOCAL_WRITE) ? I40IW_ACCESS_FLAGS_LOCALWRITE : 0;
	access |= (acc & IB_ACCESS_REMOTE_WRITE) ? I40IW_ACCESS_FLAGS_REMOTEWRITE : 0;
	access |= (acc & IB_ACCESS_REMOTE_READ) ? I40IW_ACCESS_FLAGS_REMOTEREAD : 0;
	access |= (acc & IB_ACCESS_MW_BIND) ? I40IW_ACCESS_FLAGS_BIND_WINDOW : 0;
	return access;
}