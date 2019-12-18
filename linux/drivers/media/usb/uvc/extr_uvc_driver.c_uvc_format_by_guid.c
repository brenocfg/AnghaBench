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
typedef  int /*<<< orphan*/  u8 ;
struct uvc_format_desc {int /*<<< orphan*/  guid; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct uvc_format_desc*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 struct uvc_format_desc* uvc_fmts ; 

__attribute__((used)) static struct uvc_format_desc *uvc_format_by_guid(const u8 guid[16])
{
	unsigned int len = ARRAY_SIZE(uvc_fmts);
	unsigned int i;

	for (i = 0; i < len; ++i) {
		if (memcmp(guid, uvc_fmts[i].guid, 16) == 0)
			return &uvc_fmts[i];
	}

	return NULL;
}