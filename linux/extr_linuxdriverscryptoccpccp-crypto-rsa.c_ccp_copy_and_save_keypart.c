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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__* kzalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__ const*,unsigned int) ; 

__attribute__((used)) static inline int ccp_copy_and_save_keypart(u8 **kpbuf, unsigned int *kplen,
					    const u8 *buf, size_t sz)
{
	int nskip;

	for (nskip = 0; nskip < sz; nskip++)
		if (buf[nskip])
			break;
	*kplen = sz - nskip;
	*kpbuf = kzalloc(*kplen, GFP_KERNEL);
	if (!*kpbuf)
		return -ENOMEM;
	memcpy(*kpbuf, buf + nskip, *kplen);

	return 0;
}