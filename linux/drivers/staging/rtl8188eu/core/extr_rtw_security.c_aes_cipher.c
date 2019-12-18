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
typedef  int uint ;
typedef  int u8 ;

/* Variables and functions */
 int GetFrameSubType (int*) ; 
 int GetFrameType (int*) ; 
 int WIFI_DATA_CFACK ; 
 int WIFI_DATA_CFACKPOLL ; 
 int WIFI_DATA_CFPOLL ; 
 int WLAN_HDR_A3_LEN ; 
 int WLAN_HDR_A3_QOS_LEN ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  aes128k128d (int*,int*,int*) ; 
 int /*<<< orphan*/  bitwise_xor (int*,int*,int*) ; 
 int /*<<< orphan*/  construct_ctr_preload (int*,int,int,int*,int*,int) ; 
 int /*<<< orphan*/  construct_mic_header1 (int*,int,int*) ; 
 int /*<<< orphan*/  construct_mic_header2 (int*,int*,int,int) ; 
 int /*<<< orphan*/  construct_mic_iv (int*,int,int,int*,int,int*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int aes_cipher(u8 *key, uint hdrlen, u8 *pframe, uint plen)
{
	uint	qc_exists, a4_exists, i, j, payload_remainder,
		num_blocks, payload_index;

	u8 pn_vector[6];
	u8 mic_iv[16];
	u8 mic_header1[16];
	u8 mic_header2[16];
	u8 ctr_preload[16];

	/* Intermediate Buffers */
	u8 chain_buffer[16];
	u8 aes_out[16];
	u8 padded_buffer[16];
	u8 mic[8];
	uint	frtype  = GetFrameType(pframe);
	uint	frsubtype  = GetFrameSubType(pframe);

	frsubtype >>= 4;

	memset(mic_iv, 0, 16);
	memset(mic_header1, 0, 16);
	memset(mic_header2, 0, 16);
	memset(ctr_preload, 0, 16);
	memset(chain_buffer, 0, 16);
	memset(aes_out, 0, 16);
	memset(padded_buffer, 0, 16);

	if ((hdrlen == WLAN_HDR_A3_LEN) || (hdrlen ==  WLAN_HDR_A3_QOS_LEN))
		a4_exists = 0;
	else
		a4_exists = 1;

	if ((frtype == WIFI_DATA_CFACK) || (frtype == WIFI_DATA_CFPOLL) || (frtype == WIFI_DATA_CFACKPOLL)) {
		qc_exists = 1;
		if (hdrlen !=  WLAN_HDR_A3_QOS_LEN)
			hdrlen += 2;
	} else if ((frsubtype == 0x08) || (frsubtype == 0x09) || (frsubtype == 0x0a) || (frsubtype == 0x0b)) {
		if (hdrlen !=  WLAN_HDR_A3_QOS_LEN)
			hdrlen += 2;
		qc_exists = 1;
	} else {
		qc_exists = 0;
	}

	pn_vector[0] = pframe[hdrlen];
	pn_vector[1] = pframe[hdrlen+1];
	pn_vector[2] = pframe[hdrlen+4];
	pn_vector[3] = pframe[hdrlen+5];
	pn_vector[4] = pframe[hdrlen+6];
	pn_vector[5] = pframe[hdrlen+7];

	construct_mic_iv(mic_iv, qc_exists, a4_exists, pframe, plen, pn_vector);

	construct_mic_header1(mic_header1, hdrlen, pframe);
	construct_mic_header2(mic_header2, pframe, a4_exists, qc_exists);

	payload_remainder = plen % 16;
	num_blocks = plen / 16;

	/* Find start of payload */
	payload_index = hdrlen + 8;

	/* Calculate MIC */
	aes128k128d(key, mic_iv, aes_out);
	bitwise_xor(aes_out, mic_header1, chain_buffer);
	aes128k128d(key, chain_buffer, aes_out);
	bitwise_xor(aes_out, mic_header2, chain_buffer);
	aes128k128d(key, chain_buffer, aes_out);

	for (i = 0; i < num_blocks; i++) {
		bitwise_xor(aes_out, &pframe[payload_index], chain_buffer);/* bitwise_xor(aes_out, &message[payload_index], chain_buffer); */

		payload_index += 16;
		aes128k128d(key, chain_buffer, aes_out);
	}

	/* Add on the final payload block if it needs padding */
	if (payload_remainder > 0) {
		for (j = 0; j < 16; j++)
			padded_buffer[j] = 0x00;
		for (j = 0; j < payload_remainder; j++)
			padded_buffer[j] = pframe[payload_index++];/* padded_buffer[j] = message[payload_index++]; */
		bitwise_xor(aes_out, padded_buffer, chain_buffer);
		aes128k128d(key, chain_buffer, aes_out);
	}

	for (j = 0; j < 8; j++)
		mic[j] = aes_out[j];

	/* Insert MIC into payload */
	for (j = 0; j < 8; j++)
		pframe[payload_index+j] = mic[j];

	payload_index = hdrlen + 8;
	for (i = 0; i < num_blocks; i++) {
		construct_ctr_preload(ctr_preload, a4_exists, qc_exists, pframe, pn_vector, i+1);
		aes128k128d(key, ctr_preload, aes_out);
		bitwise_xor(aes_out, &pframe[payload_index], chain_buffer);
		for (j = 0; j < 16; j++)
			pframe[payload_index++] = chain_buffer[j];
	}

	if (payload_remainder > 0) {    /* If there is a short final block, then pad it,*/
					/* encrypt it and copy the unpadded part back   */
		construct_ctr_preload(ctr_preload, a4_exists, qc_exists, pframe, pn_vector, num_blocks+1);

		for (j = 0; j < 16; j++)
			padded_buffer[j] = 0x00;
		for (j = 0; j < payload_remainder; j++)
			padded_buffer[j] = pframe[payload_index+j];
		aes128k128d(key, ctr_preload, aes_out);
		bitwise_xor(aes_out, padded_buffer, chain_buffer);
		for (j = 0; j < payload_remainder; j++)
			pframe[payload_index++] = chain_buffer[j];
	}
	/* Encrypt the MIC */
	construct_ctr_preload(ctr_preload, a4_exists, qc_exists, pframe, pn_vector, 0);

	for (j = 0; j < 16; j++)
		padded_buffer[j] = 0x00;
	for (j = 0; j < 8; j++)
		padded_buffer[j] = pframe[j+hdrlen+8+plen];

	aes128k128d(key, ctr_preload, aes_out);
	bitwise_xor(aes_out, padded_buffer, chain_buffer);
	for (j = 0; j < 8; j++)
		pframe[payload_index++] = chain_buffer[j];
	return _SUCCESS;
}