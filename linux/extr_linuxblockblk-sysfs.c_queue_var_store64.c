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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int kstrtos64 (char const*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t queue_var_store64(s64 *var, const char *page)
{
	int err;
	s64 v;

	err = kstrtos64(page, 10, &v);
	if (err < 0)
		return err;

	*var = v;
	return 0;
}