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
struct rsa_key {size_t n_sz; size_t p_sz; void const* p; } ;

/* Variables and functions */
 int EINVAL ; 

int rsa_get_p(void *context, size_t hdrlen, unsigned char tag,
	      const void *value, size_t vlen)
{
	struct rsa_key *key = context;

	/* invalid key provided */
	if (!value || !vlen || vlen > key->n_sz)
		return -EINVAL;

	key->p = value;
	key->p_sz = vlen;

	return 0;
}