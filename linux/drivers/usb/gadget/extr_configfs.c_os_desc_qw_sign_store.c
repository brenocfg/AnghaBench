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
struct gadget_info {int /*<<< orphan*/  lock; scalar_t__ qw_sign; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int OS_STRING_QW_SIGN_LEN ; 
 int /*<<< orphan*/  UTF16_LITTLE_ENDIAN ; 
 int min (int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct gadget_info* os_desc_item_to_gadget_info (struct config_item*) ; 
 int utf8s_to_utf16s (char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ssize_t os_desc_qw_sign_store(struct config_item *item, const char *page,
				     size_t len)
{
	struct gadget_info *gi = os_desc_item_to_gadget_info(item);
	int res, l;

	l = min((int)len, OS_STRING_QW_SIGN_LEN >> 1);
	if (page[l - 1] == '\n')
		--l;

	mutex_lock(&gi->lock);
	res = utf8s_to_utf16s(page, l,
			      UTF16_LITTLE_ENDIAN, (wchar_t *) gi->qw_sign,
			      OS_STRING_QW_SIGN_LEN);
	if (res > 0)
		res = len;
	mutex_unlock(&gi->lock);

	return res;
}