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
struct spu_hw {int /*<<< orphan*/  spu_wordalign_padlen; int /*<<< orphan*/  spu_ccm_update_iv; int /*<<< orphan*/  spu_xts_tweak_in_payload; int /*<<< orphan*/  spu_status_process; int /*<<< orphan*/  spu_rx_status_len; int /*<<< orphan*/  spu_tx_status_len; int /*<<< orphan*/  spu_request_pad; int /*<<< orphan*/  spu_cipher_req_finish; int /*<<< orphan*/  spu_cipher_req_init; int /*<<< orphan*/  spu_create_request; int /*<<< orphan*/  spu_digest_size; int /*<<< orphan*/  spu_hash_type; int /*<<< orphan*/  spu_aead_ivlen; int /*<<< orphan*/  spu_assoc_resp_len; int /*<<< orphan*/  spu_gcm_ccm_pad_len; int /*<<< orphan*/  spu_hash_pad_len; int /*<<< orphan*/  spu_response_hdr_len; int /*<<< orphan*/  spu_payload_length; int /*<<< orphan*/  spu_ctx_max_payload; int /*<<< orphan*/  spu_dump_msg_hdr; } ;
struct device {int dummy; } ;
typedef  enum spu_spu_type { ____Placeholder_spu_spu_type } spu_spu_type ;
typedef  enum spu_spu_subtype { ____Placeholder_spu_spu_subtype } spu_spu_subtype ;
struct TYPE_2__ {struct spu_hw spu; } ;

/* Variables and functions */
 int SPU_SUBTYPE_SPUM_NS2 ; 
 int SPU_TYPE_SPUM ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 TYPE_1__ iproc_priv ; 
 int /*<<< orphan*/  spu2_aead_ivlen ; 
 int /*<<< orphan*/  spu2_assoc_resp_len ; 
 int /*<<< orphan*/  spu2_ccm_update_iv ; 
 int /*<<< orphan*/  spu2_cipher_req_finish ; 
 int /*<<< orphan*/  spu2_cipher_req_init ; 
 int /*<<< orphan*/  spu2_create_request ; 
 int /*<<< orphan*/  spu2_ctx_max_payload ; 
 int /*<<< orphan*/  spu2_digest_size ; 
 int /*<<< orphan*/  spu2_dump_msg_hdr ; 
 int /*<<< orphan*/  spu2_gcm_ccm_pad_len ; 
 int /*<<< orphan*/  spu2_hash_pad_len ; 
 int /*<<< orphan*/  spu2_hash_type ; 
 int /*<<< orphan*/  spu2_payload_length ; 
 int /*<<< orphan*/  spu2_request_pad ; 
 int /*<<< orphan*/  spu2_response_hdr_len ; 
 int /*<<< orphan*/  spu2_rx_status_len ; 
 int /*<<< orphan*/  spu2_status_process ; 
 int /*<<< orphan*/  spu2_tx_status_len ; 
 int /*<<< orphan*/  spu2_wordalign_padlen ; 
 int /*<<< orphan*/  spu2_xts_tweak_in_payload ; 
 int /*<<< orphan*/  spum_aead_ivlen ; 
 int /*<<< orphan*/  spum_assoc_resp_len ; 
 int /*<<< orphan*/  spum_ccm_update_iv ; 
 int /*<<< orphan*/  spum_cipher_req_finish ; 
 int /*<<< orphan*/  spum_cipher_req_init ; 
 int /*<<< orphan*/  spum_create_request ; 
 int /*<<< orphan*/  spum_digest_size ; 
 int /*<<< orphan*/  spum_dump_msg_hdr ; 
 int /*<<< orphan*/  spum_gcm_ccm_pad_len ; 
 int /*<<< orphan*/  spum_hash_pad_len ; 
 int /*<<< orphan*/  spum_hash_type ; 
 int /*<<< orphan*/  spum_ns2_ctx_max_payload ; 
 int /*<<< orphan*/  spum_nsp_ctx_max_payload ; 
 int /*<<< orphan*/  spum_payload_length ; 
 int /*<<< orphan*/  spum_request_pad ; 
 int /*<<< orphan*/  spum_response_hdr_len ; 
 int /*<<< orphan*/  spum_rx_status_len ; 
 int /*<<< orphan*/  spum_status_process ; 
 int /*<<< orphan*/  spum_tx_status_len ; 
 int /*<<< orphan*/  spum_wordalign_padlen ; 
 int /*<<< orphan*/  spum_xts_tweak_in_payload ; 

__attribute__((used)) static void spu_functions_register(struct device *dev,
				   enum spu_spu_type spu_type,
				   enum spu_spu_subtype spu_subtype)
{
	struct spu_hw *spu = &iproc_priv.spu;

	if (spu_type == SPU_TYPE_SPUM) {
		dev_dbg(dev, "Registering SPUM functions");
		spu->spu_dump_msg_hdr = spum_dump_msg_hdr;
		spu->spu_payload_length = spum_payload_length;
		spu->spu_response_hdr_len = spum_response_hdr_len;
		spu->spu_hash_pad_len = spum_hash_pad_len;
		spu->spu_gcm_ccm_pad_len = spum_gcm_ccm_pad_len;
		spu->spu_assoc_resp_len = spum_assoc_resp_len;
		spu->spu_aead_ivlen = spum_aead_ivlen;
		spu->spu_hash_type = spum_hash_type;
		spu->spu_digest_size = spum_digest_size;
		spu->spu_create_request = spum_create_request;
		spu->spu_cipher_req_init = spum_cipher_req_init;
		spu->spu_cipher_req_finish = spum_cipher_req_finish;
		spu->spu_request_pad = spum_request_pad;
		spu->spu_tx_status_len = spum_tx_status_len;
		spu->spu_rx_status_len = spum_rx_status_len;
		spu->spu_status_process = spum_status_process;
		spu->spu_xts_tweak_in_payload = spum_xts_tweak_in_payload;
		spu->spu_ccm_update_iv = spum_ccm_update_iv;
		spu->spu_wordalign_padlen = spum_wordalign_padlen;
		if (spu_subtype == SPU_SUBTYPE_SPUM_NS2)
			spu->spu_ctx_max_payload = spum_ns2_ctx_max_payload;
		else
			spu->spu_ctx_max_payload = spum_nsp_ctx_max_payload;
	} else {
		dev_dbg(dev, "Registering SPU2 functions");
		spu->spu_dump_msg_hdr = spu2_dump_msg_hdr;
		spu->spu_ctx_max_payload = spu2_ctx_max_payload;
		spu->spu_payload_length = spu2_payload_length;
		spu->spu_response_hdr_len = spu2_response_hdr_len;
		spu->spu_hash_pad_len = spu2_hash_pad_len;
		spu->spu_gcm_ccm_pad_len = spu2_gcm_ccm_pad_len;
		spu->spu_assoc_resp_len = spu2_assoc_resp_len;
		spu->spu_aead_ivlen = spu2_aead_ivlen;
		spu->spu_hash_type = spu2_hash_type;
		spu->spu_digest_size = spu2_digest_size;
		spu->spu_create_request = spu2_create_request;
		spu->spu_cipher_req_init = spu2_cipher_req_init;
		spu->spu_cipher_req_finish = spu2_cipher_req_finish;
		spu->spu_request_pad = spu2_request_pad;
		spu->spu_tx_status_len = spu2_tx_status_len;
		spu->spu_rx_status_len = spu2_rx_status_len;
		spu->spu_status_process = spu2_status_process;
		spu->spu_xts_tweak_in_payload = spu2_xts_tweak_in_payload;
		spu->spu_ccm_update_iv = spu2_ccm_update_iv;
		spu->spu_wordalign_padlen = spu2_wordalign_padlen;
	}
}