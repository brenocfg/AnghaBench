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
struct iw_mgmt_info_element {int id; int len; int /*<<< orphan*/  data; } ;
typedef  enum iw_mgmt_info_element_ids { ____Placeholder_iw_mgmt_info_element_ids } iw_mgmt_info_element_ids ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static void iw_set_mgmt_info_element(enum iw_mgmt_info_element_ids id,
				     struct iw_mgmt_info_element *el,
				     void *value, int len)
{
	el->id  = id;
	el->len = len;
	memcpy(el->data, value, len);
}