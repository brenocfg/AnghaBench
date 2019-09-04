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
struct key_restriction {int dummy; } ;
typedef  struct key_restriction key ;
typedef  scalar_t__ key_serial_t ;
typedef  int /*<<< orphan*/  key_restrict_link_func_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct key_restriction* ERR_CAST (struct key_restriction*) ; 
 struct key_restriction* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct key_restriction*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct key_restriction* asymmetric_restriction_alloc (int /*<<< orphan*/ ,struct key_restriction*) ; 
 struct key_restriction* key_lookup (scalar_t__) ; 
 int /*<<< orphan*/  key_put (struct key_restriction*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrndup (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kstrtos32 (char*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  restrict_link_by_builtin_and_secondary_trusted ; 
 int /*<<< orphan*/  restrict_link_by_builtin_trusted ; 
 int /*<<< orphan*/  restrict_link_by_key_or_keyring ; 
 int /*<<< orphan*/  restrict_link_by_key_or_keyring_chain ; 
 scalar_t__ strcmp (char*,char const*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static struct key_restriction *asymmetric_lookup_restriction(
	const char *restriction)
{
	char *restrict_method;
	char *parse_buf;
	char *next;
	struct key_restriction *ret = ERR_PTR(-EINVAL);

	if (strcmp("builtin_trusted", restriction) == 0)
		return asymmetric_restriction_alloc(
			restrict_link_by_builtin_trusted, NULL);

	if (strcmp("builtin_and_secondary_trusted", restriction) == 0)
		return asymmetric_restriction_alloc(
			restrict_link_by_builtin_and_secondary_trusted, NULL);

	parse_buf = kstrndup(restriction, PAGE_SIZE, GFP_KERNEL);
	if (!parse_buf)
		return ERR_PTR(-ENOMEM);

	next = parse_buf;
	restrict_method = strsep(&next, ":");

	if ((strcmp(restrict_method, "key_or_keyring") == 0) && next) {
		char *key_text;
		key_serial_t serial;
		struct key *key;
		key_restrict_link_func_t link_fn =
			restrict_link_by_key_or_keyring;
		bool allow_null_key = false;

		key_text = strsep(&next, ":");

		if (next) {
			if (strcmp(next, "chain") != 0)
				goto out;

			link_fn = restrict_link_by_key_or_keyring_chain;
			allow_null_key = true;
		}

		if (kstrtos32(key_text, 0, &serial) < 0)
			goto out;

		if ((serial == 0) && allow_null_key) {
			key = NULL;
		} else {
			key = key_lookup(serial);
			if (IS_ERR(key)) {
				ret = ERR_CAST(key);
				goto out;
			}
		}

		ret = asymmetric_restriction_alloc(link_fn, key);
		if (IS_ERR(ret))
			key_put(key);
	}

out:
	kfree(parse_buf);
	return ret;
}