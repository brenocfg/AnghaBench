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
typedef  int /*<<< orphan*/  u16 ;
struct wmi_tlv {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  __le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 ath10k_wmi_tlv_len(const void *ptr)
{
	return __le16_to_cpu((((const struct wmi_tlv *)ptr) - 1)->len);
}