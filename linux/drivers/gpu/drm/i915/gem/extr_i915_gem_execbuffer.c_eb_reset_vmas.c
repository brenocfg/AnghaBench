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
struct i915_execbuffer {int lut_size; int /*<<< orphan*/  buckets; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  eb_release_vmas (struct i915_execbuffer const*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void eb_reset_vmas(const struct i915_execbuffer *eb)
{
	eb_release_vmas(eb);
	if (eb->lut_size > 0)
		memset(eb->buckets, 0,
		       sizeof(struct hlist_head) << eb->lut_size);
}