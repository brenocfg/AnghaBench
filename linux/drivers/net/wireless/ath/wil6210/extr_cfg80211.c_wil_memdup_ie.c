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

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
wil_memdup_ie(u8 **pdst, size_t *pdst_len, const u8 *src, size_t src_len)
{
	kfree(*pdst);
	*pdst = NULL;
	*pdst_len = 0;
	if (src_len > 0) {
		*pdst = kmemdup(src, src_len, GFP_KERNEL);
		if (*pdst)
			*pdst_len = src_len;
	}
}