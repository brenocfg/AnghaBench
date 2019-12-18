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
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct iqs5xx_ihex_rec {char start; scalar_t__ data; scalar_t__ len; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct firmware {size_t size; char* data; } ;
typedef  int /*<<< orphan*/  rec_len ;
typedef  int /*<<< orphan*/  rec_hdr ;
typedef  int /*<<< orphan*/  rec_chksm ;
typedef  int /*<<< orphan*/  rec_addr ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IQS5XX_CHKSM ; 
 scalar_t__ IQS5XX_CSTM ; 
 scalar_t__ IQS5XX_PMAP_END ; 
 int IQS5XX_REC_HDR_LEN ; 
 int IQS5XX_REC_LEN_MAX ; 
#define  IQS5XX_REC_TYPE_DATA 129 
#define  IQS5XX_REC_TYPE_EOF 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ get_unaligned_be16 (int*) ; 
 int hex2bin (int*,scalar_t__,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iqs5xx_fw_file_parse(struct i2c_client *client,
				const char *fw_file, u8 *pmap)
{
	const struct firmware *fw;
	struct iqs5xx_ihex_rec *rec;
	size_t pos = 0;
	int error, i;
	u16 rec_num = 1;
	u16 rec_addr;
	u8 rec_len, rec_type, rec_chksm, chksm;
	u8 rec_hdr[IQS5XX_REC_HDR_LEN];
	u8 rec_data[IQS5XX_REC_LEN_MAX];

	/*
	 * Firmware exported from the vendor's configuration tool deviates from
	 * standard ihex as follows: (1) the checksum for records corresponding
	 * to user-exported settings is not recalculated, and (2) an address of
	 * 0xFFFF is used for the EOF record.
	 *
	 * Because the ihex2fw tool tolerates neither (1) nor (2), the slightly
	 * nonstandard ihex firmware is parsed directly by the driver.
	 */
	error = request_firmware(&fw, fw_file, &client->dev);
	if (error) {
		dev_err(&client->dev, "Failed to request firmware %s: %d\n",
			fw_file, error);
		return error;
	}

	do {
		if (pos + sizeof(*rec) > fw->size) {
			dev_err(&client->dev, "Insufficient firmware size\n");
			error = -EINVAL;
			break;
		}
		rec = (struct iqs5xx_ihex_rec *)(fw->data + pos);
		pos += sizeof(*rec);

		if (rec->start != ':') {
			dev_err(&client->dev, "Invalid start at record %u\n",
				rec_num);
			error = -EINVAL;
			break;
		}

		error = hex2bin(rec_hdr, rec->len, sizeof(rec_hdr));
		if (error) {
			dev_err(&client->dev, "Invalid header at record %u\n",
				rec_num);
			break;
		}

		rec_len = *rec_hdr;
		rec_addr = get_unaligned_be16(rec_hdr + sizeof(rec_len));
		rec_type = *(rec_hdr + sizeof(rec_len) + sizeof(rec_addr));

		if (pos + rec_len * 2 > fw->size) {
			dev_err(&client->dev, "Insufficient firmware size\n");
			error = -EINVAL;
			break;
		}
		pos += (rec_len * 2);

		error = hex2bin(rec_data, rec->data, rec_len);
		if (error) {
			dev_err(&client->dev, "Invalid data at record %u\n",
				rec_num);
			break;
		}

		error = hex2bin(&rec_chksm,
				rec->data + rec_len * 2, sizeof(rec_chksm));
		if (error) {
			dev_err(&client->dev, "Invalid checksum at record %u\n",
				rec_num);
			break;
		}

		chksm = 0;
		for (i = 0; i < sizeof(rec_hdr); i++)
			chksm += rec_hdr[i];
		for (i = 0; i < rec_len; i++)
			chksm += rec_data[i];
		chksm = ~chksm + 1;

		if (chksm != rec_chksm && rec_addr < IQS5XX_CSTM) {
			dev_err(&client->dev,
				"Incorrect checksum at record %u\n",
				rec_num);
			error = -EINVAL;
			break;
		}

		switch (rec_type) {
		case IQS5XX_REC_TYPE_DATA:
			if (rec_addr < IQS5XX_CHKSM ||
			    rec_addr > IQS5XX_PMAP_END) {
				dev_err(&client->dev,
					"Invalid address at record %u\n",
					rec_num);
				error = -EINVAL;
			} else {
				memcpy(pmap + rec_addr - IQS5XX_CHKSM,
				       rec_data, rec_len);
			}
			break;
		case IQS5XX_REC_TYPE_EOF:
			break;
		default:
			dev_err(&client->dev, "Invalid type at record %u\n",
				rec_num);
			error = -EINVAL;
		}

		if (error)
			break;

		rec_num++;
		while (pos < fw->size) {
			if (*(fw->data + pos) == ':')
				break;
			pos++;
		}
	} while (rec_type != IQS5XX_REC_TYPE_EOF);

	release_firmware(fw);

	return error;
}