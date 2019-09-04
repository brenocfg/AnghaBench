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
struct asymmetric_key_id {scalar_t__ len; scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ memcmp (scalar_t__,scalar_t__,scalar_t__) ; 

bool asymmetric_key_id_partial(const struct asymmetric_key_id *kid1,
			       const struct asymmetric_key_id *kid2)
{
	if (!kid1 || !kid2)
		return false;
	if (kid1->len < kid2->len)
		return false;
	return memcmp(kid1->data + (kid1->len - kid2->len),
		      kid2->data, kid2->len) == 0;
}