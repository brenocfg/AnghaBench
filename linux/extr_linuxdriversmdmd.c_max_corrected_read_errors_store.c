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
struct mddev {int /*<<< orphan*/  max_corr_read_errors; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,unsigned int) ; 
 int kstrtouint (char const*,int,unsigned int*) ; 

__attribute__((used)) static ssize_t
max_corrected_read_errors_store(struct mddev *mddev, const char *buf, size_t len)
{
	unsigned int n;
	int rv;

	rv = kstrtouint(buf, 10, &n);
	if (rv < 0)
		return rv;
	atomic_set(&mddev->max_corr_read_errors, n);
	return len;
}