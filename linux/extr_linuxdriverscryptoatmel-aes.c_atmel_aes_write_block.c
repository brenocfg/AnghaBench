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
struct atmel_aes_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  SIZE_IN_WORDS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_aes_write_n (struct atmel_aes_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void atmel_aes_write_block(struct atmel_aes_dev *dd, u32 offset,
					 const u32 *value)
{
	atmel_aes_write_n(dd, offset, value, SIZE_IN_WORDS(AES_BLOCK_SIZE));
}