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
struct atmel_aes_dev {int flags; } ;

/* Variables and functions */
 int AES_FLAGS_ENCRYPT ; 

__attribute__((used)) static inline bool atmel_aes_is_encrypt(const struct atmel_aes_dev *dd)
{
	return (dd->flags & AES_FLAGS_ENCRYPT);
}