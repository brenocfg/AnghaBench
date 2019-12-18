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
struct i2c_adapter {int /*<<< orphan*/  timeout; } ;
struct i801_priv {int features; int status; TYPE_1__* pci_dev; int /*<<< orphan*/  waitq; struct i2c_adapter adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int FEATURE_IRQ ; 
 int /*<<< orphan*/  SMBHSTCNT (struct i801_priv*) ; 
 int SMBHSTCNT_INTREN ; 
 int SMBHSTCNT_START ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int i801_check_post (struct i801_priv*,int) ; 
 int i801_check_pre (struct i801_priv*) ; 
 int i801_wait_intr (struct i801_priv*) ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i801_transaction(struct i801_priv *priv, int xact)
{
	int status;
	int result;
	const struct i2c_adapter *adap = &priv->adapter;

	result = i801_check_pre(priv);
	if (result < 0)
		return result;

	if (priv->features & FEATURE_IRQ) {
		outb_p(xact | SMBHSTCNT_INTREN | SMBHSTCNT_START,
		       SMBHSTCNT(priv));
		result = wait_event_timeout(priv->waitq,
					    (status = priv->status),
					    adap->timeout);
		if (!result) {
			status = -ETIMEDOUT;
			dev_warn(&priv->pci_dev->dev,
				 "Timeout waiting for interrupt!\n");
		}
		priv->status = 0;
		return i801_check_post(priv, status);
	}

	/* the current contents of SMBHSTCNT can be overwritten, since PEC,
	 * SMBSCMD are passed in xact */
	outb_p(xact | SMBHSTCNT_START, SMBHSTCNT(priv));

	status = i801_wait_intr(priv);
	return i801_check_post(priv, status);
}