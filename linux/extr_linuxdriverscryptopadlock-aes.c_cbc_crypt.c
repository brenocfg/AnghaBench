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
typedef  int /*<<< orphan*/  u32 ;
struct cword {int dummy; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/ * cbc_crypt_copy (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct cword*,int) ; 
 scalar_t__ cbc_fetch_bytes ; 
 scalar_t__ offset_in_page (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * rep_xcrypt_cbc (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct cword*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline u8 *cbc_crypt(const u8 *in, u8 *out, u32 *key,
			    u8 *iv, struct cword *cword, int count)
{
	/* Padlock in CBC mode fetches at least cbc_fetch_bytes of data. */
	if (unlikely(offset_in_page(in) + cbc_fetch_bytes > PAGE_SIZE))
		return cbc_crypt_copy(in, out, key, iv, cword, count);

	return rep_xcrypt_cbc(in, out, key, iv, cword, count);
}