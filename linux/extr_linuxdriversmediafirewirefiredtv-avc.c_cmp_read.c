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
typedef  int /*<<< orphan*/  u64 ;
struct firedtv {int /*<<< orphan*/  device; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int fdtv_read (struct firedtv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cmp_read(struct firedtv *fdtv, u64 addr, __be32 *data)
{
	int ret;

	ret = fdtv_read(fdtv, addr, data);
	if (ret < 0)
		dev_err(fdtv->device, "CMP: read I/O error\n");

	return ret;
}