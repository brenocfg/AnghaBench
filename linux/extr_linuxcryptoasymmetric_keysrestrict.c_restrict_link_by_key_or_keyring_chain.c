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
typedef  union key_payload {int dummy; } key_payload ;
struct key_type {int dummy; } ;
struct key {int dummy; } ;

/* Variables and functions */
 int key_or_keyring_common (struct key*,struct key_type const*,union key_payload const*,struct key*,int) ; 

int restrict_link_by_key_or_keyring_chain(struct key *dest_keyring,
					  const struct key_type *type,
					  const union key_payload *payload,
					  struct key *trusted)
{
	return key_or_keyring_common(dest_keyring, type, payload, trusted,
				     true);
}