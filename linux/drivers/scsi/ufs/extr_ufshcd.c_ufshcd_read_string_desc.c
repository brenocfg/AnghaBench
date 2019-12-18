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
typedef  char u8 ;
struct ufs_hba {int /*<<< orphan*/  dev; } ;
struct uc_string_id {int len; int /*<<< orphan*/  uc; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int QUERY_DESC_HDR_SIZE ; 
 int /*<<< orphan*/  QUERY_DESC_IDN_STRING ; 
 int QUERY_DESC_MAX_SIZE ; 
 int /*<<< orphan*/  QUERY_REQ_RETRIES ; 
 int /*<<< orphan*/  UTF16_BIG_ENDIAN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct uc_string_id*) ; 
 char* kmemdup (struct uc_string_id*,int,int /*<<< orphan*/ ) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int ufshcd_read_desc (struct ufs_hba*,int /*<<< orphan*/ ,char,struct uc_string_id*,int) ; 
 char ufshcd_remove_non_printable (char) ; 
 int utf16s_to_utf8s (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int) ; 

int ufshcd_read_string_desc(struct ufs_hba *hba, u8 desc_index,
			    u8 **buf, bool ascii)
{
	struct uc_string_id *uc_str;
	u8 *str;
	int ret;

	if (!buf)
		return -EINVAL;

	uc_str = kzalloc(QUERY_DESC_MAX_SIZE, GFP_KERNEL);
	if (!uc_str)
		return -ENOMEM;

	ret = ufshcd_read_desc(hba, QUERY_DESC_IDN_STRING,
			       desc_index, uc_str,
			       QUERY_DESC_MAX_SIZE);
	if (ret < 0) {
		dev_err(hba->dev, "Reading String Desc failed after %d retries. err = %d\n",
			QUERY_REQ_RETRIES, ret);
		str = NULL;
		goto out;
	}

	if (uc_str->len <= QUERY_DESC_HDR_SIZE) {
		dev_dbg(hba->dev, "String Desc is of zero length\n");
		str = NULL;
		ret = 0;
		goto out;
	}

	if (ascii) {
		ssize_t ascii_len;
		int i;
		/* remove header and divide by 2 to move from UTF16 to UTF8 */
		ascii_len = (uc_str->len - QUERY_DESC_HDR_SIZE) / 2 + 1;
		str = kzalloc(ascii_len, GFP_KERNEL);
		if (!str) {
			ret = -ENOMEM;
			goto out;
		}

		/*
		 * the descriptor contains string in UTF16 format
		 * we need to convert to utf-8 so it can be displayed
		 */
		ret = utf16s_to_utf8s(uc_str->uc,
				      uc_str->len - QUERY_DESC_HDR_SIZE,
				      UTF16_BIG_ENDIAN, str, ascii_len);

		/* replace non-printable or non-ASCII characters with spaces */
		for (i = 0; i < ret; i++)
			str[i] = ufshcd_remove_non_printable(str[i]);

		str[ret++] = '\0';

	} else {
		str = kmemdup(uc_str, uc_str->len, GFP_KERNEL);
		if (!str) {
			ret = -ENOMEM;
			goto out;
		}
		ret = uc_str->len;
	}
out:
	*buf = str;
	kfree(uc_str);
	return ret;
}