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
typedef  int /*<<< orphan*/  wchar_t ;
struct gadget_info {scalar_t__ qw_sign; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  OS_STRING_QW_SIGN_LEN ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  UTF16_LITTLE_ENDIAN ; 
 struct gadget_info* os_desc_item_to_gadget_info (struct config_item*) ; 
 int utf16s_to_utf8s (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static ssize_t os_desc_qw_sign_show(struct config_item *item, char *page)
{
	struct gadget_info *gi = os_desc_item_to_gadget_info(item);
	int res;

	res = utf16s_to_utf8s((wchar_t *) gi->qw_sign, OS_STRING_QW_SIGN_LEN,
			      UTF16_LITTLE_ENDIAN, page, PAGE_SIZE - 1);
	page[res++] = '\n';

	return res;
}