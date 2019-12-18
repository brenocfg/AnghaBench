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
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {int tx_desc_count; } ;
struct atmel_private {scalar_t__ tx_desc_tail; int tx_rate; int group_cipher_suite; int pairwise_cipher_suite; scalar_t__ tx_desc_previous; int /*<<< orphan*/  tx_free_mem; int /*<<< orphan*/  tx_desc_free; TYPE_1__ host_info; scalar_t__ use_wpa; } ;

/* Variables and functions */
 int CIPHER_SUITE_NONE ; 
 int CIPHER_SUITE_TKIP ; 
 int CIPHER_SUITE_WEP_128 ; 
 int CIPHER_SUITE_WEP_64 ; 
 int /*<<< orphan*/  TX_DESC_CIPHER_LENGTH_OFFSET ; 
 int /*<<< orphan*/  TX_DESC_CIPHER_TYPE_OFFSET ; 
 int /*<<< orphan*/  TX_DESC_FLAGS_OFFSET ; 
 int /*<<< orphan*/  TX_DESC_HOST_LENGTH_OFFSET ; 
 int /*<<< orphan*/  TX_DESC_NEXT_OFFSET ; 
 int /*<<< orphan*/  TX_DESC_PACKET_TYPE_OFFSET ; 
 int /*<<< orphan*/  TX_DESC_POS_OFFSET ; 
 int /*<<< orphan*/  TX_DESC_RATE_OFFSET ; 
 int /*<<< orphan*/  TX_DESC_RETRY_OFFSET ; 
 int /*<<< orphan*/  TX_DESC_SIZE_OFFSET ; 
 int TX_FIRM_OWN ; 
 int /*<<< orphan*/  atmel_tx (struct atmel_private*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  atmel_wmem16 (struct atmel_private*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  atmel_wmem32 (struct atmel_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atmel_wmem8 (struct atmel_private*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tx_update_descriptor(struct atmel_private *priv, int is_bcast,
				 u16 len, u16 buff, u8 type)
{
	atmel_wmem16(priv, atmel_tx(priv, TX_DESC_POS_OFFSET, priv->tx_desc_tail), buff);
	atmel_wmem16(priv, atmel_tx(priv, TX_DESC_SIZE_OFFSET, priv->tx_desc_tail), len);
	if (!priv->use_wpa)
		atmel_wmem16(priv, atmel_tx(priv, TX_DESC_HOST_LENGTH_OFFSET, priv->tx_desc_tail), len);
	atmel_wmem8(priv, atmel_tx(priv, TX_DESC_PACKET_TYPE_OFFSET, priv->tx_desc_tail), type);
	atmel_wmem8(priv, atmel_tx(priv, TX_DESC_RATE_OFFSET, priv->tx_desc_tail), priv->tx_rate);
	atmel_wmem8(priv, atmel_tx(priv, TX_DESC_RETRY_OFFSET, priv->tx_desc_tail), 0);
	if (priv->use_wpa) {
		int cipher_type, cipher_length;
		if (is_bcast) {
			cipher_type = priv->group_cipher_suite;
			if (cipher_type == CIPHER_SUITE_WEP_64 ||
			    cipher_type == CIPHER_SUITE_WEP_128)
				cipher_length = 8;
			else if (cipher_type == CIPHER_SUITE_TKIP)
				cipher_length = 12;
			else if (priv->pairwise_cipher_suite == CIPHER_SUITE_WEP_64 ||
				 priv->pairwise_cipher_suite == CIPHER_SUITE_WEP_128) {
				cipher_type = priv->pairwise_cipher_suite;
				cipher_length = 8;
			} else {
				cipher_type = CIPHER_SUITE_NONE;
				cipher_length = 0;
			}
		} else {
			cipher_type = priv->pairwise_cipher_suite;
			if (cipher_type == CIPHER_SUITE_WEP_64 ||
			    cipher_type == CIPHER_SUITE_WEP_128)
				cipher_length = 8;
			else if (cipher_type == CIPHER_SUITE_TKIP)
				cipher_length = 12;
			else if (priv->group_cipher_suite == CIPHER_SUITE_WEP_64 ||
				 priv->group_cipher_suite == CIPHER_SUITE_WEP_128) {
				cipher_type = priv->group_cipher_suite;
				cipher_length = 8;
			} else {
				cipher_type = CIPHER_SUITE_NONE;
				cipher_length = 0;
			}
		}

		atmel_wmem8(priv, atmel_tx(priv, TX_DESC_CIPHER_TYPE_OFFSET, priv->tx_desc_tail),
			    cipher_type);
		atmel_wmem8(priv, atmel_tx(priv, TX_DESC_CIPHER_LENGTH_OFFSET, priv->tx_desc_tail),
			    cipher_length);
	}
	atmel_wmem32(priv, atmel_tx(priv, TX_DESC_NEXT_OFFSET, priv->tx_desc_tail), 0x80000000L);
	atmel_wmem8(priv, atmel_tx(priv, TX_DESC_FLAGS_OFFSET, priv->tx_desc_tail), TX_FIRM_OWN);
	if (priv->tx_desc_previous != priv->tx_desc_tail)
		atmel_wmem32(priv, atmel_tx(priv, TX_DESC_NEXT_OFFSET, priv->tx_desc_previous), 0);
	priv->tx_desc_previous = priv->tx_desc_tail;
	if (priv->tx_desc_tail < (priv->host_info.tx_desc_count - 1))
		priv->tx_desc_tail++;
	else
		priv->tx_desc_tail = 0;
	priv->tx_desc_free--;
	priv->tx_free_mem -= len;
}