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
struct crypto_aead {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int MORUS_MAX_AUTH_SIZE ; 

__attribute__((used)) static int crypto_morus1280_setauthsize(struct crypto_aead *tfm,
					unsigned int authsize)
{
	return (authsize <= MORUS_MAX_AUTH_SIZE) ? 0 : -EINVAL;
}