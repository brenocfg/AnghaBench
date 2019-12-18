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
typedef  int /*<<< orphan*/  u8 ;
struct go7007 {int format; int /*<<< orphan*/  dev; } ;
struct firmware {int size; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int FLAG_MODE_MJPEG ; 
 int FLAG_MODE_MPEG1 ; 
 int FLAG_MODE_MPEG2 ; 
 int FLAG_MODE_MPEG4 ; 
 int FLAG_SPECIAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GO7007_FW_NAME ; 
#define  V4L2_PIX_FMT_MJPEG 131 
#define  V4L2_PIX_FMT_MPEG1 130 
#define  V4L2_PIX_FMT_MPEG2 129 
#define  V4L2_PIX_FMT_MPEG4 128 
 int __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int do_special (struct go7007*,int,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 scalar_t__ request_firmware (struct firmware const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int go7007_construct_fw_image(struct go7007 *go, u8 **fw, int *fwlen)
{
	const struct firmware *fw_entry;
	__le16 *code, *src;
	int framelen[8] = { }; /* holds the lengths of empty frame templates */
	int codespace = 64 * 1024, i = 0, srclen, chunk_len, chunk_flags;
	int mode_flag;
	int ret;

	switch (go->format) {
	case V4L2_PIX_FMT_MJPEG:
		mode_flag = FLAG_MODE_MJPEG;
		break;
	case V4L2_PIX_FMT_MPEG1:
		mode_flag = FLAG_MODE_MPEG1;
		break;
	case V4L2_PIX_FMT_MPEG2:
		mode_flag = FLAG_MODE_MPEG2;
		break;
	case V4L2_PIX_FMT_MPEG4:
		mode_flag = FLAG_MODE_MPEG4;
		break;
	default:
		return -1;
	}
	if (request_firmware(&fw_entry, GO7007_FW_NAME, go->dev)) {
		dev_err(go->dev,
			"unable to load firmware from file \"%s\"\n",
			GO7007_FW_NAME);
		return -1;
	}
	code = kcalloc(codespace, 2, GFP_KERNEL);
	if (code == NULL)
		goto fw_failed;

	src = (__le16 *)fw_entry->data;
	srclen = fw_entry->size / 2;
	while (srclen >= 2) {
		chunk_flags = __le16_to_cpu(src[0]);
		chunk_len = __le16_to_cpu(src[1]);
		if (chunk_len + 2 > srclen) {
			dev_err(go->dev,
				"firmware file \"%s\" appears to be corrupted\n",
				GO7007_FW_NAME);
			goto fw_failed;
		}
		if (chunk_flags & mode_flag) {
			if (chunk_flags & FLAG_SPECIAL) {
				ret = do_special(go, __le16_to_cpu(src[2]),
					&code[i], codespace - i, framelen);
				if (ret < 0) {
					dev_err(go->dev,
						"insufficient memory for firmware construction\n");
					goto fw_failed;
				}
				i += ret;
			} else {
				if (codespace - i < chunk_len) {
					dev_err(go->dev,
						"insufficient memory for firmware construction\n");
					goto fw_failed;
				}
				memcpy(&code[i], &src[2], chunk_len * 2);
				i += chunk_len;
			}
		}
		srclen -= chunk_len + 2;
		src += chunk_len + 2;
	}
	release_firmware(fw_entry);
	*fw = (u8 *)code;
	*fwlen = i * 2;
	return 0;

fw_failed:
	kfree(code);
	release_firmware(fw_entry);
	return -1;
}