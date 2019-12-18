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
struct i915_syncmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int check_syncmap_free (struct i915_syncmap**) ; 
 int /*<<< orphan*/  i915_syncmap_free (struct i915_syncmap**) ; 
 scalar_t__ i915_syncmap_print_to_buf (struct i915_syncmap*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,char*) ; 

__attribute__((used)) static int dump_syncmap(struct i915_syncmap *sync, int err)
{
	char *buf;

	if (!err)
		return check_syncmap_free(&sync);

	buf = kmalloc(PAGE_SIZE, GFP_KERNEL);
	if (!buf)
		goto skip;

	if (i915_syncmap_print_to_buf(sync, buf, PAGE_SIZE))
		pr_err("%s", buf);

	kfree(buf);

skip:
	i915_syncmap_free(&sync);
	return err;
}