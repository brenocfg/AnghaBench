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
typedef  enum jpeg_decoding_error_t { ____Placeholder_jpeg_decoding_error_t } jpeg_decoding_error_t ;

/* Variables and functions */
#define  JPEG_DECODER_BAD_COMPONENT_COUNT 139 
#define  JPEG_DECODER_BAD_COUNT_VALUE 138 
#define  JPEG_DECODER_BAD_DHT_MARKER 137 
#define  JPEG_DECODER_BAD_HEADER_LENGTH 136 
#define  JPEG_DECODER_BAD_INDEX_VALUE 135 
#define  JPEG_DECODER_BAD_NUMBER_HUFFMAN_TABLES 134 
#define  JPEG_DECODER_BAD_NUMBER_QUANT_TABLES 133 
#define  JPEG_DECODER_BAD_QUANT_TABLE_LENGTH 132 
#define  JPEG_DECODER_BAD_RESTART_MARKER 131 
#define  JPEG_DECODER_BAD_SOS_SPECTRAL 130 
#define  JPEG_DECODER_BAD_SOS_SUCCESSIVE 129 
#define  JPEG_DECODER_UNDEFINED_HUFF_TABLE 128 

__attribute__((used)) static inline bool is_stream_error(enum jpeg_decoding_error_t err)
{
	switch (err) {
	case JPEG_DECODER_UNDEFINED_HUFF_TABLE:
	case JPEG_DECODER_BAD_RESTART_MARKER:
	case JPEG_DECODER_BAD_SOS_SPECTRAL:
	case JPEG_DECODER_BAD_SOS_SUCCESSIVE:
	case JPEG_DECODER_BAD_HEADER_LENGTH:
	case JPEG_DECODER_BAD_COUNT_VALUE:
	case JPEG_DECODER_BAD_DHT_MARKER:
	case JPEG_DECODER_BAD_INDEX_VALUE:
	case JPEG_DECODER_BAD_NUMBER_HUFFMAN_TABLES:
	case JPEG_DECODER_BAD_QUANT_TABLE_LENGTH:
	case JPEG_DECODER_BAD_NUMBER_QUANT_TABLES:
	case JPEG_DECODER_BAD_COMPONENT_COUNT:
		return true;
	default:
		return false;
	}
}