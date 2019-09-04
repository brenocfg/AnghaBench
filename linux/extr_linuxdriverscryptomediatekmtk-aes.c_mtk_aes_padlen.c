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

/* Variables and functions */
 int AES_BLOCK_SIZE ; 

__attribute__((used)) static inline size_t mtk_aes_padlen(size_t len)
{
	len &= AES_BLOCK_SIZE - 1;
	return len ? AES_BLOCK_SIZE - len : 0;
}