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
struct crypt_config {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int crypt_set_keyring_key(struct crypt_config *cc, const char *key_string)
{
	return -EINVAL;
}