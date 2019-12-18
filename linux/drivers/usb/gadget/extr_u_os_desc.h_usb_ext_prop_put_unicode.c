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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int USB_EXT_PROP_B_PROPERTY_DATA ; 
 int /*<<< orphan*/  UTF16_LITTLE_ENDIAN ; 
 int /*<<< orphan*/  put_unaligned_le16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_ext_prop_data_len_ptr (int /*<<< orphan*/ *,int) ; 
 scalar_t__ usb_ext_prop_data_ptr (int /*<<< orphan*/ *,int) ; 
 int utf8s_to_utf16s (char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int usb_ext_prop_put_unicode(u8 *buf, int pnl, const char *string,
					   int data_len)
{
	int result;
	put_unaligned_le32(data_len, usb_ext_prop_data_len_ptr(buf, pnl));
	result = utf8s_to_utf16s(string, data_len >> 1, UTF16_LITTLE_ENDIAN,
			(wchar_t *) usb_ext_prop_data_ptr(buf, pnl),
			data_len - 2);
	if (result < 0)
		return result;

	put_unaligned_le16(0,
		&buf[USB_EXT_PROP_B_PROPERTY_DATA + pnl + data_len - 2]);

	return data_len;
}