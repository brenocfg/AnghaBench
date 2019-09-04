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
typedef  int /*<<< orphan*/  u32 ;
struct coda_memcpy_desc {int offset; int len; int /*<<< orphan*/ * src; } ;

/* Variables and functions */
 int /*<<< orphan*/  swab32 (int /*<<< orphan*/  const) ; 

__attribute__((used)) static void coda_memcpy_parabuf(void *parabuf,
				const struct coda_memcpy_desc *desc)
{
	u32 *dst = parabuf + desc->offset;
	const u32 *src = desc->src;
	int len = desc->len / 4;
	int i;

	for (i = 0; i < len; i += 2) {
		dst[i + 1] = swab32(src[i]);
		dst[i] = swab32(src[i + 1]);
	}
}