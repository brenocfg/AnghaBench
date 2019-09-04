#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_9__ {scalar_t__ mode; scalar_t__ count; scalar_t__ latency; } ;
struct TYPE_10__ {scalar_t__ block_size; scalar_t__ stripe_size; scalar_t__ vendor_id; scalar_t__ cache_order; TYPE_1__ intr_coal; } ;
struct TYPE_12__ {scalar_t__ version; scalar_t__ crc; } ;
struct TYPE_11__ {TYPE_2__ data; TYPE_5__ hdr; } ;
struct rsxx_cardinfo {int config_valid; TYPE_3__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_TO_DEV (struct rsxx_cardinfo*) ; 
 int /*<<< orphan*/  CREG_ADD_CONFIG ; 
 int EINVAL ; 
 int EIO ; 
 scalar_t__ RSXX_CFG_VERSION ; 
 scalar_t__ config_data_crc32 (TYPE_3__*) ; 
 int /*<<< orphan*/  config_data_le_to_cpu (TYPE_3__*) ; 
 int /*<<< orphan*/  config_data_swab (TYPE_3__*) ; 
 int /*<<< orphan*/  config_hdr_be_to_cpu (TYPE_5__*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  initialize_config (TYPE_3__*) ; 
 int rsxx_creg_read (struct rsxx_cardinfo*,int /*<<< orphan*/ ,int,TYPE_3__*,int) ; 
 int rsxx_save_config (struct rsxx_cardinfo*) ; 

int rsxx_load_config(struct rsxx_cardinfo *card)
{
	int st;
	u32 crc;

	st = rsxx_creg_read(card, CREG_ADD_CONFIG, sizeof(card->config),
				&card->config, 1);
	if (st) {
		dev_err(CARD_TO_DEV(card),
			"Failed reading card config.\n");
		return st;
	}

	config_hdr_be_to_cpu(&card->config.hdr);

	if (card->config.hdr.version == RSXX_CFG_VERSION) {
		/*
		 * We calculate the CRC with the data in little endian, because
		 * early drivers did not take big endian CPUs into account.
		 * The data is always stored in big endian, so we need to byte
		 * swap it before calculating the CRC.
		 */

		config_data_swab(&card->config);

		/* Check the CRC */
		crc = config_data_crc32(&card->config);
		if (crc != card->config.hdr.crc) {
			dev_err(CARD_TO_DEV(card),
				"Config corruption detected!\n");
			dev_info(CARD_TO_DEV(card),
				"CRC (sb x%08x is x%08x)\n",
				card->config.hdr.crc, crc);
			return -EIO;
		}

		/* Convert the data to CPU byteorder */
		config_data_le_to_cpu(&card->config);

	} else if (card->config.hdr.version != 0) {
		dev_err(CARD_TO_DEV(card),
			"Invalid config version %d.\n",
			card->config.hdr.version);
		/*
		 * Config version changes require special handling from the
		 * user
		 */
		return -EINVAL;
	} else {
		dev_info(CARD_TO_DEV(card),
			"Initializing card configuration.\n");
		initialize_config(&card->config);
		st = rsxx_save_config(card);
		if (st)
			return st;
	}

	card->config_valid = 1;

	dev_dbg(CARD_TO_DEV(card), "version:     x%08x\n",
		card->config.hdr.version);
	dev_dbg(CARD_TO_DEV(card), "crc:         x%08x\n",
		card->config.hdr.crc);
	dev_dbg(CARD_TO_DEV(card), "block_size:  x%08x\n",
		card->config.data.block_size);
	dev_dbg(CARD_TO_DEV(card), "stripe_size: x%08x\n",
		card->config.data.stripe_size);
	dev_dbg(CARD_TO_DEV(card), "vendor_id:   x%08x\n",
		card->config.data.vendor_id);
	dev_dbg(CARD_TO_DEV(card), "cache_order: x%08x\n",
		card->config.data.cache_order);
	dev_dbg(CARD_TO_DEV(card), "mode:        x%08x\n",
		card->config.data.intr_coal.mode);
	dev_dbg(CARD_TO_DEV(card), "count:       x%08x\n",
		card->config.data.intr_coal.count);
	dev_dbg(CARD_TO_DEV(card), "latency:     x%08x\n",
		 card->config.data.intr_coal.latency);

	return 0;
}