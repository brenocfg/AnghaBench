#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct public_key_signature {int dummy; } ;
struct public_key {int dummy; } ;
struct TYPE_2__ {struct public_key** data; } ;
struct key {TYPE_1__ payload; } ;

/* Variables and functions */
 size_t asym_crypto ; 
 int public_key_verify_signature (struct public_key const*,struct public_key_signature const*) ; 

__attribute__((used)) static int public_key_verify_signature_2(const struct key *key,
					 const struct public_key_signature *sig)
{
	const struct public_key *pk = key->payload.data[asym_crypto];
	return public_key_verify_signature(pk, sig);
}