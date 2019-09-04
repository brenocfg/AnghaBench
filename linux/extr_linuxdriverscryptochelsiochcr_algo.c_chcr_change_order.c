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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  __be64 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int SHA512_DIGEST_SIZE ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void chcr_change_order(char *buf, int ds)
{
	int i;

	if (ds == SHA512_DIGEST_SIZE) {
		for (i = 0; i < (ds / sizeof(u64)); i++)
			*((__be64 *)buf + i) =
				cpu_to_be64(*((u64 *)buf + i));
	} else {
		for (i = 0; i < (ds / sizeof(u32)); i++)
			*((__be32 *)buf + i) =
				cpu_to_be32(*((u32 *)buf + i));
	}
}