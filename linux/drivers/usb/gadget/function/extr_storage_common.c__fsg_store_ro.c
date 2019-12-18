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
struct fsg_lun {int ro; int initially_ro; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  LDBG (struct fsg_lun*,char*,...) ; 
 scalar_t__ fsg_lun_is_open (struct fsg_lun*) ; 

__attribute__((used)) static ssize_t _fsg_store_ro(struct fsg_lun *curlun, bool ro)
{
	if (fsg_lun_is_open(curlun)) {
		LDBG(curlun, "read-only status change prevented\n");
		return -EBUSY;
	}

	curlun->ro = ro;
	curlun->initially_ro = ro;
	LDBG(curlun, "read-only status set to %d\n", curlun->ro);

	return 0;
}