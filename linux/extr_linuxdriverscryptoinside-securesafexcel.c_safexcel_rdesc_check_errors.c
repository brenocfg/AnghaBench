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
struct TYPE_2__ {int error_code; } ;
struct safexcel_result_desc {TYPE_1__ result_data; } ;
struct safexcel_crypto_priv {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EBADMSG ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ likely (int) ; 

inline int safexcel_rdesc_check_errors(struct safexcel_crypto_priv *priv,
				       struct safexcel_result_desc *rdesc)
{
	if (likely(!rdesc->result_data.error_code))
		return 0;

	if (rdesc->result_data.error_code & 0x407f) {
		/* Fatal error (bits 0-7, 14) */
		dev_err(priv->dev,
			"cipher: result: result descriptor error (%d)\n",
			rdesc->result_data.error_code);
		return -EIO;
	} else if (rdesc->result_data.error_code == BIT(9)) {
		/* Authentication failed */
		return -EBADMSG;
	}

	/* All other non-fatal errors */
	return -EINVAL;
}