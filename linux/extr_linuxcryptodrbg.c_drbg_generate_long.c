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
struct drbg_string {int dummy; } ;
struct drbg_state {int /*<<< orphan*/  drbg_mutex; } ;

/* Variables and functions */
 int drbg_generate (struct drbg_state*,unsigned char*,unsigned int,struct drbg_string*) ; 
 unsigned int drbg_max_request_bytes (struct drbg_state*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int drbg_generate_long(struct drbg_state *drbg,
			      unsigned char *buf, unsigned int buflen,
			      struct drbg_string *addtl)
{
	unsigned int len = 0;
	unsigned int slice = 0;
	do {
		int err = 0;
		unsigned int chunk = 0;
		slice = ((buflen - len) / drbg_max_request_bytes(drbg));
		chunk = slice ? drbg_max_request_bytes(drbg) : (buflen - len);
		mutex_lock(&drbg->drbg_mutex);
		err = drbg_generate(drbg, buf + len, chunk, addtl);
		mutex_unlock(&drbg->drbg_mutex);
		if (0 > err)
			return err;
		len += chunk;
	} while (slice > 0 && (len < buflen));
	return 0;
}