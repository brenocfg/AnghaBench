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
struct iscsi_conn {int /*<<< orphan*/ * conn_tx_hash; int /*<<< orphan*/ * conn_rx_hash; } ;
struct crypto_ahash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_ASYNC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct crypto_ahash*) ; 
 void* ahash_request_alloc (struct crypto_ahash*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahash_request_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ahash_request_set_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct crypto_ahash* crypto_alloc_ahash (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_ahash (struct crypto_ahash*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int iscsi_login_setup_crypto(struct iscsi_conn *conn)
{
	struct crypto_ahash *tfm;

	/*
	 * Setup slicing by CRC32C algorithm for RX and TX libcrypto contexts
	 * which will default to crc32c_intel.ko for cpu_has_xmm4_2, or fallback
	 * to software 1x8 byte slicing from crc32c.ko
	 */
	tfm = crypto_alloc_ahash("crc32c", 0, CRYPTO_ALG_ASYNC);
	if (IS_ERR(tfm)) {
		pr_err("crypto_alloc_ahash() failed\n");
		return -ENOMEM;
	}

	conn->conn_rx_hash = ahash_request_alloc(tfm, GFP_KERNEL);
	if (!conn->conn_rx_hash) {
		pr_err("ahash_request_alloc() failed for conn_rx_hash\n");
		crypto_free_ahash(tfm);
		return -ENOMEM;
	}
	ahash_request_set_callback(conn->conn_rx_hash, 0, NULL, NULL);

	conn->conn_tx_hash = ahash_request_alloc(tfm, GFP_KERNEL);
	if (!conn->conn_tx_hash) {
		pr_err("ahash_request_alloc() failed for conn_tx_hash\n");
		ahash_request_free(conn->conn_rx_hash);
		conn->conn_rx_hash = NULL;
		crypto_free_ahash(tfm);
		return -ENOMEM;
	}
	ahash_request_set_callback(conn->conn_tx_hash, 0, NULL, NULL);

	return 0;
}