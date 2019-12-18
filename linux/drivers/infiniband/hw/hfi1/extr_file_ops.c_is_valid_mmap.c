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

/* Variables and functions */
 scalar_t__ HFI1_MMAP_MAGIC ; 
 scalar_t__ HFI1_MMAP_TOKEN_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAGIC ; 

__attribute__((used)) static inline int is_valid_mmap(u64 token)
{
	return (HFI1_MMAP_TOKEN_GET(MAGIC, token) == HFI1_MMAP_MAGIC);
}