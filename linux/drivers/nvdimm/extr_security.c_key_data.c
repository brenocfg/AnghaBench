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
struct key {int /*<<< orphan*/  sem; } ;
struct encrypted_key_payload {void* decrypted_data; } ;

/* Variables and functions */
 struct encrypted_key_payload* dereference_key_locked (struct key*) ; 
 int /*<<< orphan*/  lockdep_assert_held_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *key_data(struct key *key)
{
	struct encrypted_key_payload *epayload = dereference_key_locked(key);

	lockdep_assert_held_read(&key->sem);

	return epayload->decrypted_data;
}