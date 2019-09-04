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
struct TYPE_2__ {struct asymmetric_key_ids** data; } ;
struct key {TYPE_1__ payload; } ;
struct asymmetric_key_subtype {int /*<<< orphan*/  owner; int /*<<< orphan*/  (* destroy ) (void*,void*) ;} ;
struct asymmetric_key_ids {int dummy; } ;

/* Variables and functions */
 size_t asym_auth ; 
 size_t asym_crypto ; 
 size_t asym_key_ids ; 
 size_t asym_subtype ; 
 int /*<<< orphan*/  asymmetric_key_free_kids (struct asymmetric_key_ids*) ; 
 struct asymmetric_key_subtype* asymmetric_key_subtype (struct key*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (void*,void*) ; 

__attribute__((used)) static void asymmetric_key_destroy(struct key *key)
{
	struct asymmetric_key_subtype *subtype = asymmetric_key_subtype(key);
	struct asymmetric_key_ids *kids = key->payload.data[asym_key_ids];
	void *data = key->payload.data[asym_crypto];
	void *auth = key->payload.data[asym_auth];

	key->payload.data[asym_crypto] = NULL;
	key->payload.data[asym_subtype] = NULL;
	key->payload.data[asym_key_ids] = NULL;
	key->payload.data[asym_auth] = NULL;

	if (subtype) {
		subtype->destroy(data, auth);
		module_put(subtype->owner);
	}

	asymmetric_key_free_kids(kids);
}