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
struct drm_property_blob {scalar_t__ length; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool blob_equal(const struct drm_property_blob *a,
		       const struct drm_property_blob *b)
{
	if (a && b)
		return a->length == b->length &&
			!memcmp(a->data, b->data, a->length);

	return !a == !b;
}