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
struct i2c_device {int dummy; } ;

/* Variables and functions */
 int I801_START ; 
 int MAX_RETRIES ; 
 int /*<<< orphan*/  SMBHSTCNT (struct i2c_device*) ; 
 int /*<<< orphan*/  SMBHSTSTS (struct i2c_device*) ; 
 int SMBHSTSTS_HOST_BUSY ; 
 int SMBHSTSTS_INTR ; 
 int i801_check_post (struct i2c_device*,int,int) ; 
 int i801_check_pre (struct i2c_device*) ; 
 int inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int i801_transaction(struct i2c_device *priv, int xact)
{
	int status;
	int result;
	int timeout = 0;

	result = i801_check_pre(priv);
	if (result < 0)
		return result;
	/* the current contents of SMBHSTCNT can be overwritten, since PEC,
	 * INTREN, SMBSCMD are passed in xact
	 */
	outb_p(xact | I801_START, SMBHSTCNT(priv));

	/* We will always wait for a fraction of a second! */
	do {
		usleep_range(250, 500);
		status = inb_p(SMBHSTSTS(priv));
	} while ((status & SMBHSTSTS_HOST_BUSY) && (timeout++ < MAX_RETRIES));

	result = i801_check_post(priv, status, timeout > MAX_RETRIES);
	if (result < 0)
		return result;

	outb_p(SMBHSTSTS_INTR, SMBHSTSTS(priv));
	return 0;
}