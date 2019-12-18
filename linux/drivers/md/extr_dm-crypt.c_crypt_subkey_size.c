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
struct crypt_config {int key_size; int key_extra_size; int /*<<< orphan*/  tfms_count; } ;

/* Variables and functions */
 int ilog2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned crypt_subkey_size(struct crypt_config *cc)
{
	return (cc->key_size - cc->key_extra_size) >> ilog2(cc->tfms_count);
}