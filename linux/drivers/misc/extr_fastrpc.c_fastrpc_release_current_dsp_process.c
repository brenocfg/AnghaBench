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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  tgid ;
struct fastrpc_user {int tgid; } ;
struct fastrpc_invoke_args {int length; int fd; scalar_t__ reserved; scalar_t__ ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  FASTRPC_INIT_HANDLE ; 
 int /*<<< orphan*/  FASTRPC_RMID_INIT_RELEASE ; 
 int /*<<< orphan*/  FASTRPC_SCALARS (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int fastrpc_internal_invoke (struct fastrpc_user*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fastrpc_invoke_args*) ; 

__attribute__((used)) static int fastrpc_release_current_dsp_process(struct fastrpc_user *fl)
{
	struct fastrpc_invoke_args args[1];
	int tgid = 0;
	u32 sc;

	tgid = fl->tgid;
	args[0].ptr = (u64)(uintptr_t) &tgid;
	args[0].length = sizeof(tgid);
	args[0].fd = -1;
	args[0].reserved = 0;
	sc = FASTRPC_SCALARS(FASTRPC_RMID_INIT_RELEASE, 1, 0);

	return fastrpc_internal_invoke(fl, true, FASTRPC_INIT_HANDLE,
				       sc, &args[0]);
}