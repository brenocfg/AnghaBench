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
struct venus_caps {size_t num_caps; int /*<<< orphan*/ * caps; } ;
struct hfi_capability {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct hfi_capability const*,unsigned int) ; 

__attribute__((used)) static void
fill_caps(struct venus_caps *cap, const void *data, unsigned int num)
{
	const struct hfi_capability *caps = data;

	memcpy(&cap->caps[cap->num_caps], caps, num * sizeof(*caps));
	cap->num_caps += num;
}