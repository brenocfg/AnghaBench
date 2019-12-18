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
struct iw_mgmt_info_element {int /*<<< orphan*/  len; int /*<<< orphan*/  data; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  iw_set_mgmt_info_element (int /*<<< orphan*/ ,struct iw_mgmt_info_element*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iw_copy_mgmt_info_element(struct iw_mgmt_info_element *to,
				      struct iw_mgmt_info_element *from)
{
	iw_set_mgmt_info_element(from->id, to, from->data, from->len);
}