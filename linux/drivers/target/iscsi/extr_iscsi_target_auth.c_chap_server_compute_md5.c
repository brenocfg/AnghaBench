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
struct shash_desc {struct crypto_shash* tfm; } ;
struct iscsi_node_auth {unsigned char* userid; unsigned char* password; unsigned char* password_mutual; unsigned char* userid_mutual; int /*<<< orphan*/  authenticate_target; } ;
struct iscsi_conn {struct iscsi_chap* auth_protocol; } ;
struct iscsi_chap {unsigned char id; unsigned char* challenge; } ;
struct crypto_shash {int dummy; } ;

/* Variables and functions */
 int CHAP_CHALLENGE_LENGTH ; 
 int CHAP_CHALLENGE_STR_LEN ; 
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned char HEX ; 
 scalar_t__ IS_ERR (struct crypto_shash*) ; 
 int MAX_CHAP_N_SIZE ; 
 int MAX_RESPONSE_LENGTH ; 
 int MD5_SIGNATURE_SIZE ; 
 int /*<<< orphan*/  bin2hex (unsigned char*,unsigned char*,int) ; 
 struct crypto_shash* crypto_alloc_shash (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_shash (struct crypto_shash*) ; 
 scalar_t__ crypto_shash_descsize (struct crypto_shash*) ; 
 int crypto_shash_finup (struct shash_desc*,unsigned char*,int,unsigned char*) ; 
 int crypto_shash_init (struct shash_desc*) ; 
 int crypto_shash_update (struct shash_desc*,...) ; 
 scalar_t__ extract_param (char*,char*,int,unsigned char*,unsigned char*) ; 
 scalar_t__ hex2bin (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 struct shash_desc* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int kstrtoul (unsigned char*,int /*<<< orphan*/ ,unsigned long*) ; 
 unsigned char* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (struct shash_desc*) ; 
 scalar_t__ memcmp (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 unsigned int sprintf (char*,char*,unsigned char*) ; 
 int strlen (unsigned char*) ; 
 scalar_t__ strncmp (unsigned char*,unsigned char*,size_t) ; 

__attribute__((used)) static int chap_server_compute_md5(
	struct iscsi_conn *conn,
	struct iscsi_node_auth *auth,
	char *nr_in_ptr,
	char *nr_out_ptr,
	unsigned int *nr_out_len)
{
	unsigned long id;
	unsigned char id_as_uchar;
	unsigned char digest[MD5_SIGNATURE_SIZE];
	unsigned char type, response[MD5_SIGNATURE_SIZE * 2 + 2];
	unsigned char identifier[10], *challenge = NULL;
	unsigned char *challenge_binhex = NULL;
	unsigned char client_digest[MD5_SIGNATURE_SIZE];
	unsigned char server_digest[MD5_SIGNATURE_SIZE];
	unsigned char chap_n[MAX_CHAP_N_SIZE], chap_r[MAX_RESPONSE_LENGTH];
	size_t compare_len;
	struct iscsi_chap *chap = conn->auth_protocol;
	struct crypto_shash *tfm = NULL;
	struct shash_desc *desc = NULL;
	int auth_ret = -1, ret, challenge_len;

	memset(identifier, 0, 10);
	memset(chap_n, 0, MAX_CHAP_N_SIZE);
	memset(chap_r, 0, MAX_RESPONSE_LENGTH);
	memset(digest, 0, MD5_SIGNATURE_SIZE);
	memset(response, 0, MD5_SIGNATURE_SIZE * 2 + 2);
	memset(client_digest, 0, MD5_SIGNATURE_SIZE);
	memset(server_digest, 0, MD5_SIGNATURE_SIZE);

	challenge = kzalloc(CHAP_CHALLENGE_STR_LEN, GFP_KERNEL);
	if (!challenge) {
		pr_err("Unable to allocate challenge buffer\n");
		goto out;
	}

	challenge_binhex = kzalloc(CHAP_CHALLENGE_STR_LEN, GFP_KERNEL);
	if (!challenge_binhex) {
		pr_err("Unable to allocate challenge_binhex buffer\n");
		goto out;
	}
	/*
	 * Extract CHAP_N.
	 */
	if (extract_param(nr_in_ptr, "CHAP_N", MAX_CHAP_N_SIZE, chap_n,
				&type) < 0) {
		pr_err("Could not find CHAP_N.\n");
		goto out;
	}
	if (type == HEX) {
		pr_err("Could not find CHAP_N.\n");
		goto out;
	}

	/* Include the terminating NULL in the compare */
	compare_len = strlen(auth->userid) + 1;
	if (strncmp(chap_n, auth->userid, compare_len) != 0) {
		pr_err("CHAP_N values do not match!\n");
		goto out;
	}
	pr_debug("[server] Got CHAP_N=%s\n", chap_n);
	/*
	 * Extract CHAP_R.
	 */
	if (extract_param(nr_in_ptr, "CHAP_R", MAX_RESPONSE_LENGTH, chap_r,
				&type) < 0) {
		pr_err("Could not find CHAP_R.\n");
		goto out;
	}
	if (type != HEX) {
		pr_err("Could not find CHAP_R.\n");
		goto out;
	}
	if (strlen(chap_r) != MD5_SIGNATURE_SIZE * 2) {
		pr_err("Malformed CHAP_R\n");
		goto out;
	}
	if (hex2bin(client_digest, chap_r, MD5_SIGNATURE_SIZE) < 0) {
		pr_err("Malformed CHAP_R\n");
		goto out;
	}

	pr_debug("[server] Got CHAP_R=%s\n", chap_r);

	tfm = crypto_alloc_shash("md5", 0, 0);
	if (IS_ERR(tfm)) {
		tfm = NULL;
		pr_err("Unable to allocate struct crypto_shash\n");
		goto out;
	}

	desc = kmalloc(sizeof(*desc) + crypto_shash_descsize(tfm), GFP_KERNEL);
	if (!desc) {
		pr_err("Unable to allocate struct shash_desc\n");
		goto out;
	}

	desc->tfm = tfm;

	ret = crypto_shash_init(desc);
	if (ret < 0) {
		pr_err("crypto_shash_init() failed\n");
		goto out;
	}

	ret = crypto_shash_update(desc, &chap->id, 1);
	if (ret < 0) {
		pr_err("crypto_shash_update() failed for id\n");
		goto out;
	}

	ret = crypto_shash_update(desc, (char *)&auth->password,
				  strlen(auth->password));
	if (ret < 0) {
		pr_err("crypto_shash_update() failed for password\n");
		goto out;
	}

	ret = crypto_shash_finup(desc, chap->challenge,
				 CHAP_CHALLENGE_LENGTH, server_digest);
	if (ret < 0) {
		pr_err("crypto_shash_finup() failed for challenge\n");
		goto out;
	}

	bin2hex(response, server_digest, MD5_SIGNATURE_SIZE);
	pr_debug("[server] MD5 Server Digest: %s\n", response);

	if (memcmp(server_digest, client_digest, MD5_SIGNATURE_SIZE) != 0) {
		pr_debug("[server] MD5 Digests do not match!\n\n");
		goto out;
	} else
		pr_debug("[server] MD5 Digests match, CHAP connection"
				" successful.\n\n");
	/*
	 * One way authentication has succeeded, return now if mutual
	 * authentication is not enabled.
	 */
	if (!auth->authenticate_target) {
		auth_ret = 0;
		goto out;
	}
	/*
	 * Get CHAP_I.
	 */
	if (extract_param(nr_in_ptr, "CHAP_I", 10, identifier, &type) < 0) {
		pr_err("Could not find CHAP_I.\n");
		goto out;
	}

	if (type == HEX)
		ret = kstrtoul(&identifier[2], 0, &id);
	else
		ret = kstrtoul(identifier, 0, &id);

	if (ret < 0) {
		pr_err("kstrtoul() failed for CHAP identifier: %d\n", ret);
		goto out;
	}
	if (id > 255) {
		pr_err("chap identifier: %lu greater than 255\n", id);
		goto out;
	}
	/*
	 * RFC 1994 says Identifier is no more than octet (8 bits).
	 */
	pr_debug("[server] Got CHAP_I=%lu\n", id);
	/*
	 * Get CHAP_C.
	 */
	if (extract_param(nr_in_ptr, "CHAP_C", CHAP_CHALLENGE_STR_LEN,
			challenge, &type) < 0) {
		pr_err("Could not find CHAP_C.\n");
		goto out;
	}

	if (type != HEX) {
		pr_err("Could not find CHAP_C.\n");
		goto out;
	}
	challenge_len = DIV_ROUND_UP(strlen(challenge), 2);
	if (!challenge_len) {
		pr_err("Unable to convert incoming challenge\n");
		goto out;
	}
	if (challenge_len > 1024) {
		pr_err("CHAP_C exceeds maximum binary size of 1024 bytes\n");
		goto out;
	}
	if (hex2bin(challenge_binhex, challenge, challenge_len) < 0) {
		pr_err("Malformed CHAP_C\n");
		goto out;
	}
	pr_debug("[server] Got CHAP_C=%s\n", challenge);
	/*
	 * During mutual authentication, the CHAP_C generated by the
	 * initiator must not match the original CHAP_C generated by
	 * the target.
	 */
	if (!memcmp(challenge_binhex, chap->challenge, CHAP_CHALLENGE_LENGTH)) {
		pr_err("initiator CHAP_C matches target CHAP_C, failing"
		       " login attempt\n");
		goto out;
	}
	/*
	 * Generate CHAP_N and CHAP_R for mutual authentication.
	 */
	ret = crypto_shash_init(desc);
	if (ret < 0) {
		pr_err("crypto_shash_init() failed\n");
		goto out;
	}

	/* To handle both endiannesses */
	id_as_uchar = id;
	ret = crypto_shash_update(desc, &id_as_uchar, 1);
	if (ret < 0) {
		pr_err("crypto_shash_update() failed for id\n");
		goto out;
	}

	ret = crypto_shash_update(desc, auth->password_mutual,
				  strlen(auth->password_mutual));
	if (ret < 0) {
		pr_err("crypto_shash_update() failed for"
				" password_mutual\n");
		goto out;
	}
	/*
	 * Convert received challenge to binary hex.
	 */
	ret = crypto_shash_finup(desc, challenge_binhex, challenge_len,
				 digest);
	if (ret < 0) {
		pr_err("crypto_shash_finup() failed for ma challenge\n");
		goto out;
	}

	/*
	 * Generate CHAP_N and CHAP_R.
	 */
	*nr_out_len = sprintf(nr_out_ptr, "CHAP_N=%s", auth->userid_mutual);
	*nr_out_len += 1;
	pr_debug("[server] Sending CHAP_N=%s\n", auth->userid_mutual);
	/*
	 * Convert response from binary hex to ascii hext.
	 */
	bin2hex(response, digest, MD5_SIGNATURE_SIZE);
	*nr_out_len += sprintf(nr_out_ptr + *nr_out_len, "CHAP_R=0x%s",
			response);
	*nr_out_len += 1;
	pr_debug("[server] Sending CHAP_R=0x%s\n", response);
	auth_ret = 0;
out:
	kzfree(desc);
	if (tfm)
		crypto_free_shash(tfm);
	kfree(challenge);
	kfree(challenge_binhex);
	return auth_ret;
}