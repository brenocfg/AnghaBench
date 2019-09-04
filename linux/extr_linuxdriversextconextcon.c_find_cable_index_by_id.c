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
struct extcon_dev {int max_supported; unsigned int const* supported_cable; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int find_cable_index_by_id(struct extcon_dev *edev, const unsigned int id)
{
	int i;

	/* Find the the index of extcon cable in edev->supported_cable */
	for (i = 0; i < edev->max_supported; i++) {
		if (edev->supported_cable[i] == id)
			return i;
	}

	return -EINVAL;
}